#include <transcode_audio/run_example.hpp>

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libavutil/audio_fifo.h>
EXTERN_C_END

#include <string>
#include <iostream>

#include <common/Exceptionator.hpp>

#include <transcode_audio/OpenInputFile.hpp>
#include <transcode_audio/OpenOutputFile.hpp>
#include <transcode_audio/InitResampler.hpp>
#include <transcode_audio/InitFifo.hpp>
#include <transcode_audio/WriteOutputFileHeader.hpp>
#include <transcode_audio/ReadDecodeConvertAndStore.hpp>
#include <transcode_audio/LoadEncodeAndWrite.hpp>
#include <transcode_audio/AudioFrameEncoder.hpp>



void tr_au_ex::run_example()
{
    AVFormatContext *input_format_context = nullptr;
    AVFormatContext *output_format_context = nullptr;

    AVCodecContext *input_codec_context = nullptr;
    AVCodecContext *output_codec_context = nullptr;

    SwrContext *resample_context = nullptr;

    AVAudioFifo *fifo = nullptr;

    int ret = 0;

    try {
        const std::string input_file_name{" "};
        const std::string output_file_name{" "};


        /* Open the input file for reading. */
        ret = tr_au::open_input_file(input_file_name.c_str(), &input_format_context, &input_codec_context);
        if (ret != 0) {
            common::Exceptionator ex {};
            ex << "Fail open input file: " << input_file_name;
            ex.make_runtime_err();
        }


        /* Open the output file for writing. */
        ret = tr_au::open_output_file(
                output_file_name.c_str(),
                input_codec_context,
                &output_format_context,
                &output_codec_context
        );
        if (ret != 0){
            common::Exceptionator ex {};
            ex << "Fail open output file: " << output_file_name;
            ex.make_runtime_err();
        }


        /* Initialize the resampler to be able to convert audio sample formats. */
        ret = tr_au::init_resampler(
                input_codec_context,
                output_codec_context,
                &resample_context
        );
        if (ret != 0){
            common::Exceptionator ex {};
            ex << "Fail init re-sampler.";
            ex.make_runtime_err();
        }


        /* Initialize the FIFO buffer to store audio samples to be encoded. */
        ret = tr_au::init_fifo(&fifo, output_codec_context);
        if (ret != 0){
            common::Exceptionator ex {};
            ex << "Fail init fifo";
            ex.make_runtime_err();
        }


        /* Write the header of the output file container. */
        ret = tr_au::write_output_file_header(output_format_context);
        if (ret != 0){
            common::Exceptionator ex {};
            ex << "Fail write output file header.";
            ex.make_runtime_err();
        }

        /* Loop as long as we have input samples to read or output samples
         * to write; abort as soon as we have neither. */
        tr_au::AudioFrameEncoder audio_frame_encoder{};
        bool run = true;
        while (run) {
            /* Use the encoder's desired frame size for processing. */
            const int output_frame_size = output_codec_context->frame_size;
            int finished = 0;

            /* Make sure that there is one frame worth of samples in the FIFO
             * buffer so that the encoder can do its work.
             * Since the decoder's and the encoder's frame size may differ, we
             * need to FIFO buffer to store as many frames worth of input samples
             * that they make up at least one frame worth of output samples. */
            while (av_audio_fifo_size(fifo) < output_frame_size) {
                /* Decode one frame worth of audio samples, convert it to the
                 * output sample format and put it into the FIFO buffer. */
                ret = tr_au::read_decode_convert_and_store(
                        fifo,
                        input_format_context,
                        input_codec_context,
                        output_codec_context,
                        resample_context,
                        &finished
                );
                if (ret != 0){
                    common::Exceptionator ex {};
                    ex << "Fail read_decode_convert_and_store().";
                    ex.make_runtime_err();
                }

                /* If we are at the end of the input file, we continue
                 * encoding the remaining audio samples to the output file. */
                if (finished){
                    run = false;
                    break;
                }
            }

            /* If we have enough samples for the encoder, we encode them.
             * At the end of the file, we pass the remaining samples to
             * the encoder. */
            while (av_audio_fifo_size(fifo) >= output_frame_size
                || (finished && av_audio_fifo_size(fifo) > 0)) {
                /* Take one frame worth of audio samples from the FIFO buffer,
                 * encode it and write it to the output file. */
                ret = tr_au::load_encode_and_write(
                        audio_frame_encoder,
                        fifo,
                        output_format_context,
                        output_codec_context
                );
                if (ret != 0){
                    common::Exceptionator ex {};
                    ex << "Fail load_encode_and_write().";
                    ex.make_runtime_err();
                }
            }

            /* If we are at the end of the input file and have encoded
             * all remaining samples, we can exit this loop and finish. */
            if (finished) {
                int data_written;
                /* Flush the encoder as it may have delayed frames. */
                do {
                    data_written = 0;
                    if (encode_audio_frame(NULL, output_format_context,
                                           output_codec_context, &data_written))
                        goto cleanup;
                } while (data_written);
                break;
            }
        }

        /* Write the trailer of the output file container. */
        if (write_output_file_trailer(output_format_context))
            goto cleanup;
        ret = 0;

    }
    catch (const std::runtime_error & err) {
        std::cerr << "Catch exception: " << err.what() << std::endl;

        if (fifo) {
            av_audio_fifo_free(fifo);
        }

        swr_free(&resample_context);

        if (output_codec_context) {
            avcodec_free_context(&output_codec_context);
        }

        if (output_format_context) {
            avio_closep(&output_format_context->pb);
            avformat_free_context(output_format_context);
        }

        if (input_codec_context) {
            avcodec_free_context(&input_codec_context);
        }

        if (input_format_context) {
            avformat_close_input(&input_format_context);
        }
    }  // end catch

}

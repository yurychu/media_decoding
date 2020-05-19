import sys
import os
import subprocess
from pathlib import Path


ffmpeg_exe = "ffmpeg"


def make_result_directory(input_file_path):
    input_path_parent = Path(input_file_path).parent
    input_stem = Path(input_file_path).stem
    res_dir = os.path.join(input_path_parent, input_stem + "_result")
    Path(res_dir).mkdir()
    return res_dir


def concat_on_dir(result_dir, file_name):
    return os.path.join(result_dir, file_name)


def run_subproc(commands):
    process = subprocess.Popen(commands, stdout=subprocess.PIPE)
    process.wait()
    for line in process.stdout:
        print(line)


def extract_audio_stream(orig_file, result_stream_name):
    print("Processing for audio stream: ", orig_file)
    cmd = [ffmpeg_exe, '-i', orig_file, "-vn", "-acodec", "copy", result_stream_name]
    run_subproc(cmd)


def extract_video_stream(orig_file, result_stream_name):
    print("Processing for video stream: ", orig_file)
    cmd = [ffmpeg_exe, '-i', orig_file, "-an", "-vcodec", "copy", result_stream_name]
    run_subproc(cmd)


def to_wav(input_file_name, result_wav_name):
    print("Processing to wav: ", input_file_name)
    cmd = [ffmpeg_exe, "-i", input_file_name, result_wav_name]
    run_subproc(cmd)


def encode_back(input_name, result_name):
    print("Processing to aac back: ", input_name)
    cmd = [ffmpeg_exe, "-i", input_name, "-codec:a", "aac", result_name]
    run_subproc(cmd)


def merge_all(video_container_name, audio_container_name, result_merge_name):
    print("Processing merge all to:", result_merge_name)
    cmd = [
        ffmpeg_exe,
        "-i", video_container_name,
        "-i", audio_container_name,
        "-map", "0:v",
        "-map", "1:a",
        "-c", "copy",
        result_merge_name
    ]
    run_subproc(cmd)


if __name__ == "__main__":
    input_file = sys.argv[1]

    to_directory = make_result_directory(input_file)

    audio_stream_name = concat_on_dir(to_directory, "split_aud.mp4")
    video_stream_name = concat_on_dir(to_directory, "split_vid.mp4")
    raw_audio_name = concat_on_dir(to_directory, "dec_raw.wav")
    encoded_audio_name = concat_on_dir(to_directory, "enc_aac.mp4")
    result_file_name = concat_on_dir(to_directory, "result_merge.mp4")

    extract_audio_stream(input_file, audio_stream_name)
    extract_video_stream(input_file, video_stream_name)

    to_wav(audio_stream_name, raw_audio_name)
    encode_back(raw_audio_name, encoded_audio_name)
    merge_all(video_stream_name, encoded_audio_name, result_file_name)

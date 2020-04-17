#include <iostream>
#include <cstdlib>

#include "media_explore/MediaExplorer.hpp"
#include <QApplication>
#include <QProgressBar>
#include <QSlider>
#include <QMediaPlayer>
#include <QVideoWidget>

#include "ui/Window.hpp"

#include <transcode_audio/run_example.hpp>

#if 0
int main(int argc, char*argv[]) {

//    const std::string file_name = "I:\\Sounds\\waves\\out_ai_mori_au.m4a";
//    const std::string file_name = "I:\\Sounds\\waves\\ai_mori_check_out2.wav";
//     const std::string file_name = "E:\\ORBOX\\video_testing\\hdr\\Sony_Swordsmith_HDR_UHD_4K_Demo.mp4";
//    const std::string file_name = R"(E:\ORBOX\hd422\MPEG2-HD422-Lizhnik_.mxf)";
//    const std::string file_name = R"(I:\TestVideoFiles\Tecom\NKSFIL000328.mp4)";
    const std::string file_name = R"(I:\TestVideoFiles\Tecom\7\ai_mori_check.mp4)";
//    MediaObject media_object { file_name };
//    media_object.print_info();

//    media_object.start_read_packets();
//

    QApplication app (argc, argv);
    auto player = new QMediaPlayer{};

//    auto playlist = new QMediaPlaylist(player);
//    playlist->addMedia(QUrl("http://example.com/myclip1.mp4"));
//    playlist->addMedia(QUrl("http://example.com/myclip2.mp4"));

    auto videoWidget = new QVideoWidget{};
    player->setVideoOutput(videoWidget);
    videoWidget->show();
    videoWidget->setMinimumSize(800, 600);


//    playlist->setCurrentIndex(1);
//    player->play();


//    std::cout << player << std::endl;
    player->setMedia(
            QUrl::fromLocalFile(QString::fromStdString(file_name))
    );


    player->setVolume(75);
    player->play();
//

//
//    md_ui::Window window {};
////
////    auto progressBar = new QProgressBar(&window);
////    progressBar->setRange(0, 100);
////    progressBar->setValue(0);
////    progressBar->setGeometry(10, 10, 180, 30);
////
////    auto slider = new QSlider{&window};
////    slider->setOrientation(Qt::Horizontal);
////    slider->setRange(0, 100);
////    slider->setValue(0);
////    slider->setGeometry(10, 40, 180, 30);
//
//    window.show();
//
////    auto window_moc = window.metaObject();
////
////    QObject::connect(
////            slider, SIGNAL (valueChanged(int)),
////            progressBar, SLOT (setValue(int))
////    );
//
    return QApplication::exec();
//    return 0;
}

#elif 0

int main()
{
    tr_au_ex::run_example();

    return 0;
}

#elif 01

#include <common/LocalFile.hpp>

int main()
{
    try {
        common::LocalFile local_file {"my some file"};
        std::cout << local_file.name() << std::endl;
    }
    catch (const std::runtime_error & ex){
        std::cout << "Exception msg: " << ex.what() << std::endl;
    }

    return 0;
}

#endif

/**
set QT_DEBUG_PLUGINS=1  - print actions

*/

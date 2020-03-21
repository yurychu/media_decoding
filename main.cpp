#include <iostream>
#include <cstdlib>

#include "media_explore/MediaExplorer.hpp"
#include <QApplication>
#include <QProgressBar>
#include <QSlider>


#include "ui/Window.hpp"


int main(int argc, char*argv[]) {

    // const std::string file_name = "E:\\ORBOX\\video_testing\\hdr\\Sony_Swordsmith_HDR_UHD_4K_Demo.mp4";
//    const std::string file_name = R"(E:\ORBOX\hd422\MPEG2-HD422-Lizhnik_.mxf)";
//    MediaObject media_object { file_name };
//    media_object.print_info();
//
//    media_object.start_read_packets();

    QApplication app (argc, argv);

    md_ui::Window window {};
//
//    auto progressBar = new QProgressBar(&window);
//    progressBar->setRange(0, 100);
//    progressBar->setValue(0);
//    progressBar->setGeometry(10, 10, 180, 30);
//
//    auto slider = new QSlider{&window};
//    slider->setOrientation(Qt::Horizontal);
//    slider->setRange(0, 100);
//    slider->setValue(0);
//    slider->setGeometry(10, 40, 180, 30);

    window.show();

//    auto window_moc = window.metaObject();
//
//    QObject::connect(
//            slider, SIGNAL (valueChanged(int)),
//            progressBar, SLOT (setValue(int))
//    );

    return QApplication::exec();
}


/**
set QT_DEBUG_PLUGINS=1  - print actions

*/
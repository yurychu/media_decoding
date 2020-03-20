#include <iostream>
#include <cstdlib>

#include "media_explore/MediaExplorer.hpp"
#include <QApplication>
#include <QPushButton>


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
    window.show();

    return app.exec();
}

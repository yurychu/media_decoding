cmake_minimum_required(VERSION 3.15)
project(desktop_client_proj)

set(CMAKE_INCLUDE_CURRENT_DIR ON)  # Qt dependency

##find_package(Qt5Widgets REQUIRED)
##find_package(Qt5Multimedia REQUIRED)
##find_package(Qt5MultimediaWidgets REQUIRED)
## or option too:
find_package(Qt5
        REQUIRED
        COMPONENTS
        Widgets Multimedia MultimediaWidgets
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)  # User Interface Compiler (uic), read ui and create .h file.
set(CMAKE_AUTORCC ON)


# desktop-client
add_executable(
        dsk_client

#        WIN32  # to hide console appear

#        src/main.cpp
#        src/main2.cpp
#        src/simple_main.cpp
        src/run_forms_main.cpp

        spreadsheet.qrc

        include/desktop_client/u_interfaces/ClientInterface.ui

        include/desktop_client/ExperimentWindow.hpp
        src/ExperimentWindow.cpp

        include/desktop_client/ClientWindow.hpp
        src/ClientWindow.cpp

        include/desktop_client/FindDialog.hpp
        src/FindDialog.cpp

        include/desktop_client/SimpleCode.hpp
        src/SimpleCode.cpp

        include/desktop_client/GoToCellDialog.hpp
        src/GoToCellDialog.cpp
        include/desktop_client/u_interfaces/GoToCellDialog.ui

        include/desktop_client/SortDialog.hpp
        src/SortDialog.cpp
        include/desktop_client/u_interfaces/SortDialog.ui

        include/desktop_client/MainWindowSpreadSheet.hpp
        src/MainWindowSpreadSheet.cpp

        include/desktop_client/SpreadSheet.hpp
        src/SpreadSheet.cpp

        include/desktop_client/Cell.hpp
        src/Cell.cpp

        include/desktop_client/HexSpinBox.hpp
        src/HexSpinBox.cpp

        include/desktop_client/IconEditor.hpp
        src/IconEditor.cpp

        include/desktop_client/SelectFilesWidget.hpp
        src/SelectFilesWidget.cpp

        include/desktop_client/MxfSpecMainWindow.hpp
        src/MxfSpecMainWindow.cpp

        include/desktop_client/SettingsBlockWidget.hpp
        src/SettingsBlockWidget.cpp

        include/desktop_client/AllSettingsMxfParametersWidgets.hpp

        include/desktop_client/StructureSettingsSaver.hpp
        src/StructureSettingsSaver.cpp

        include/desktop_client/SaveableJSONWidget.hpp
        src/SaveableJSONWidget.cpp

        # blocks for settings
        include/desktop_client/blocks_for_settings/CheckBox.hpp
        src/blocks_for_settings/CheckBox.cpp

        include/desktop_client/blocks_for_settings/LabeledComboBox.hpp
        src/blocks_for_settings/LabeledComboBox.cpp

        include/desktop_client/blocks_for_settings/LabeledWidthHeight.hpp
        src/blocks_for_settings/LabeledWidthHeight.cpp

        include/desktop_client/blocks_for_settings/LabeledIntEditLine.hpp
        src/blocks_for_settings/LabeledIntEditLine.cpp

        include/desktop_client/blocks_for_settings/LabeledComparator.hpp
        src/blocks_for_settings/LabeledComparator.cpp

        # settings widgets
        include/desktop_client/settings_widgets/FormatVersionSettings.hpp
        src/settings_widgets/FormatVersionSettings.cpp

        include/desktop_client/settings_widgets/RIPPresenceSettings.hpp
        src/settings_widgets/RIPPresenceSettings.cpp

        include/desktop_client/settings_widgets/ResolutionSettings.hpp
        src/settings_widgets/ResolutionSettings.cpp

        include/desktop_client/settings_widgets/VideoLineMapSettings.hpp
        src/settings_widgets/VideoLineMapSettings.cpp

        include/desktop_client/settings_widgets/IndexTableValuesSettings.hpp
        src/settings_widgets/IndexTableValuesSettings.cpp

)

target_include_directories(
        dsk_client
        PRIVATE
        include
)

target_link_libraries(
        dsk_client
        PUBLIC
        Qt5::Widgets
        Qt5::Multimedia
        Qt5::MultimediaWidgets

)


# mxf parameters
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/desktop_client/cmake/Modules/")

find_package(uriparser 0.9.4 CONFIG REQUIRED char wchar_t)
find_package(MXF_C REQUIRED)
find_package(MXF_CPP REQUIRED)
find_package(expat 2.2.6 CONFIG REQUIRED)
find_package(BMX REQUIRED)
find_package(MXF_SPEC REQUIRED)


add_executable(
        mxf_parameters
        src/mxf_main.cpp

        include/desktop_client/SelectFilesWidget.hpp
        src/SelectFilesWidget.cpp

        include/desktop_client/MxfSpecMainWindow.hpp
        src/MxfSpecMainWindow.cpp

        include/desktop_client/SettingsBlockWidget.hpp
        src/SettingsBlockWidget.cpp

        include/desktop_client/AllSettingsMxfParametersWidgets.hpp

        include/desktop_client/StructureSettingsSaver.hpp
        src/StructureSettingsSaver.cpp

        include/desktop_client/SaveableJSONWidget.hpp
        src/SaveableJSONWidget.cpp

        # blocks for settings
        include/desktop_client/blocks_for_settings/CheckBox.hpp
        src/blocks_for_settings/CheckBox.cpp

        include/desktop_client/blocks_for_settings/LabeledComboBox.hpp
        src/blocks_for_settings/LabeledComboBox.cpp

        include/desktop_client/blocks_for_settings/LabeledWidthHeight.hpp
        src/blocks_for_settings/LabeledWidthHeight.cpp

        include/desktop_client/blocks_for_settings/LabeledIntEditLine.hpp
        src/blocks_for_settings/LabeledIntEditLine.cpp

        include/desktop_client/blocks_for_settings/LabeledComparator.hpp
        src/blocks_for_settings/LabeledComparator.cpp

        # settings widgets
        include/desktop_client/settings_widgets/FormatVersionSettings.hpp
        src/settings_widgets/FormatVersionSettings.cpp

        include/desktop_client/settings_widgets/RIPPresenceSettings.hpp
        src/settings_widgets/RIPPresenceSettings.cpp

        include/desktop_client/settings_widgets/ResolutionSettings.hpp
        src/settings_widgets/ResolutionSettings.cpp

        include/desktop_client/settings_widgets/VideoLineMapSettings.hpp
        src/settings_widgets/VideoLineMapSettings.cpp

        include/desktop_client/settings_widgets/IndexTableValuesSettings.hpp
        src/settings_widgets/IndexTableValuesSettings.cpp

        # checker
        include/desktop_client/checker_mxf_file.hpp
        src/checker_mxf_file.cpp

)

target_include_directories(
        mxf_parameters
        PRIVATE
        include
)

target_link_libraries(
        mxf_parameters
        PUBLIC
        Qt5::Widgets
        MXF::mxf_c
        MXF::mxf_cpp
        MXF::bmx
        uriparser::uriparser
        expat::libexpat
        MXF::mxf_spec
)

# Timeline Track Editor
This is a general GUI template that has a timeline and track editor for anyone to use to get started on their project.
A timeline in the GUI of an application is something that many people used and needed, 
but there was not free open-source code available that was easy to implement.

# Required Libraries

wxwidgets https://www.wxwidgets.org/


# How to Install

1. Install required libraries.
2. Clone this repository
3. cd timeline-track-editor
4. mkdir build
5. cd build
6. cmake .. -DwxWidgets_CONFIG_EXECUTABLE=path-to-wxconfig-executable
    
    FreeBSD: path-to-wxconfig-executable = /usr/local/bin/wxgtk3u-3.1-config
    
    Linux: path-to-wxconfig-executable = /usr/bin/wx-config-gtk3
7. make
8. ./timeline-track-editor


========================================================================
    WIN32 APPLICATION : Win32RandonList Project Overview
========================================================================


This file contains a summary of what you will find in each of the files that
make up your Win32RandonList application.


Win32RandonList.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Win32RandonList.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Win32RandonList.cpp
    This is the main application source file.主界面的实现

/////////////////////////////////////////////////////////////////////////////
AppWizard has created the following resources:

Win32RandonList.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++.资源和菜单在这里

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

Win32RandonList.ico
    This is an icon file, which is used as the application's icon (32x32).
    This icon is included by the main resource file Win32RandonList.rc.

small.ico
    This is an icon file, which contains a smaller version (16x16)
    of the application's icon. This icon is included by the main resource
    file Win32RandonList.rc.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Win32RandonList.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
config.h
所有可以调节的参数在这里定义，具体释义在文件内
CsvReader.cpp
实现Csv文件的读取和写入，实现在内存中的数据结构表示和相关操作，是主界面调用的唯一接口。
Codec.cpp
实现文字编码的检测
RowHelper.cpp
帮助实例化Row对象
EditRow.cpp
实现Row对象，代表每一行.

/////////////////////////////////////////////////////////////////////////////

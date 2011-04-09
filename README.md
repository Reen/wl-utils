

Script to setup my boost lib directory on mac. It uses install_name_tool to correct
the library search paths in the file. These search paths are later on included at
link time, when a program is linked to one of the libs. Having no path information
in the dylib will give "dyld: Library not loaded" errors.

    #!/bin/bash
    
    for i in $(find . -name "libboost_*.dylib" -print)
    do
        install_name_tool -id $(readlink -f $i) $i
        libs=$(otool -L $i | tail -n +2 | awk '{print $1}' | grep -E "^libboost" | grep -v $(basename $i))
        echo $i
        for j in $libs
        do
            echo "    $j"
            install_name_tool -change $j $(readlink -f $j) $i
        done
    done

More literature on this issue:
http://lists.apple.com/archives/xcode-users/2009/aug/msg00174.html
http://blogs.sun.com/dipol/entry/dynamic_libraries_rpath_and_mac

# windeployqt.cmake

function(deploy_qt_app target)
    if(WIN32 AND Qt6_FOUND)
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${Qt6_DIR}/../../../bin/windeployqt.exe $<TARGET_FILE:${target}>
            COMMENT "Running windeployqt for ${target}"
        )
    endif()
endfunction()
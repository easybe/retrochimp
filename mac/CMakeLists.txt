cmake_minimum_required(VERSION 3.10)

add_application(Retrochimp
  app.c
  app.r
  form.c
  form.r
  menu.c
  menu.r
  serial.c
  )

# Enable -ffunction-sections and -gc-sections to make the app as small as possible
# On 68K, also enable --mac-single to build it as a single-segment app (so that this code path doesn't rot)
set_target_properties(Retrochimp PROPERTIES COMPILE_OPTIONS -ffunction-sections)
if(CMAKE_SYSTEM_NAME MATCHES Retro68)
  set_target_properties(Retrochimp PROPERTIES LINK_FLAGS "-Wl,-gc-sections -Wl,--mac-single")
else()
  set_target_properties(Retrochimp PROPERTIES LINK_FLAGS "-Wl,-gc-sections")
endif()

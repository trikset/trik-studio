#ifndef TCP_ROBOT_SIMULATOR_EXPORT
#  if defined(TCP_ROBOT_SIMULATOR_LIBRARY)
#    define TCP_ROBOT_SIMULATOR_EXPORT Q_DECL_EXPORT
#  else
#    define TCP_ROBOT_SIMULATOR_EXPORT Q_DECL_IMPORT
#  endif
#endif

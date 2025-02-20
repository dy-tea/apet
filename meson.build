project('apet', 'cpp', 'c')

wayland_client = dependency('wayland-client')
wayland_protocols = dependency('wayland-protocols')
f3d = dependency('f3d', method: 'cmake', modules: ['f3d::libf3d'])

wl_protocol_dir = wayland_protocols.get_variable('pkgdatadir')

wayland_scanner = find_program('wayland-scanner')

client_protocols = [
  wl_protocol_dir / 'stable' / 'xdg-shell' / 'xdg-shell.xml',
  'protocols' / 'wlr-layer-shell-unstable-v1.xml',
]

code = []
headers = []

foreach filename : client_protocols
  client_code = custom_target(
    filename.underscorify() + '_c',
    input: filename,
    output: '@BASENAME@-protocol.c',
    command: [wayland_scanner, 'private-code', '@INPUT@', '@OUTPUT@'],
  )
  code += [client_code]

  client_header = custom_target(
    filename.underscorify() + '_h',
    input: filename,
    output: '@BASENAME@-client-protocol.h',
    command: [wayland_scanner, 'client-header', '@INPUT@', '@OUTPUT@'],
  )
  headers += [client_header]
endforeach

include = include_directories(
  'include',
)

libs = [wayland_client, wayland_protocols, f3d]

executable(
  'apet',
  [
    'src' / 'main.cpp',
    code,
    headers,
  ],
  include_directories: include,
  dependencies: libs,
)

{
  "target_defaults": {
    "sources": [
      "src/NuoJsAddon.cpp",
      "src/NuoJsDriver.cpp",
      "src/NuoJsConnection.cpp"
    ]
  },
  "targets": [{
    "target_name": "nuodb",
    "include_dirs" : [
      "src",
      "<!(node -e \"require('nan')\")"
    ],
  }]
}
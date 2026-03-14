group "default" {
    targets = [ "sony" ]
}

target "sony" {
    context = "."
    dockerfile = "Dockerfile"
    tags= ["pysonycrsdk:latest"]
}

target "multiarch" {
    inherits = [ "sony" ]
    platforms = [ "linux/arm64", "linux/amd64" ]
}

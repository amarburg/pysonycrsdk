group "default" {
    targets = [ "dev" ]
}

target "dev" {
    context = "."
    dockerfile = "Dockerfile"
    target = "development"
    tags= ["pysonycrsdk:dev"]
}

target "multiarch" {
    inherits = [ "sony" ]
    platforms = [ "linux/arm64", "linux/amd64" ]
}

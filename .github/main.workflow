workflow "Main workflow" {
  on = "push"
  resolves = [
    "lint:editorconfig",
    "Include What You Use",
    "arm-none-eabi",
  ]
}

action "lint:editorconfig" {
  uses = "actions/npm@master"
  args = ["apt-get update && apt-get install -y git && npm install && npm run lint:editorconfig"]
  runs = "bash -c"
}

action "Include What You Use" {
  uses = "./.github/actions/iwyu"
  args = "/work/projects/cmake -Dbuild_test_namespace_test=OFF"
}

action "arm-none-eabi" {
  uses = "./.github/actions/arm-none-eabi"
  args = "cd test && make showcxxversion showcxxmacros && make"
}

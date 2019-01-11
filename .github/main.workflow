workflow "New workflow" {
  on = "push"
  resolves = ["Hello World"]
}

action "shell" {
  uses = "actions/bin/sh@master"
  args = "ls"
}

action "Hello World" {
  uses = "./.ci/gihub/actions/run-test"
  env = {
    MY_NAME = "srz_zumix"
  }
  args = "\"Hello world, I'm $MY_NAME!\""
  needs = ["shell"]
}

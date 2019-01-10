workflow "New workflow" {
  on = "push"
  resolves = ["Hello World"]
}

action "Hello World" {
  uses = "./actions/run-test"
  env = {
    MY_NAME = "srz_zumix"
  }
  args = "\"Hello world, I'm $MY_NAME!\""
}

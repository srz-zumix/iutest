workflow "New workflow" {
  on = "push"
  resolves = [
    "Hello World",
    "lint:editorconfig",
  ]
}

action "Hello World" {
  uses = "./helloworld"
  env = {
    MY_NAME = "srz_zumix"
  }
  args = "\"Hello world, I'm $MY_NAME!\""
}

action "GitHub Action for npm install" {
  uses = "actions/npm@e7aaefed7c9f2e83d493ff810f17fa5ccd7ed437"
  args = "install"
}

action "lint:editorconfig" {
  uses = "actions/npm@e7aaefed7c9f2e83d493ff810f17fa5ccd7ed437"
  args = "lint:editorconfig"
  needs = ["GitHub Action for npm install"]
}

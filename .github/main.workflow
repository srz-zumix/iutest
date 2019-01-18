workflow "New workflow" {
  on = "push"
  resolves = [
    "lint:editorconfig",
  ]
}

action "GitHub Action for npm apt-get install git" {
  uses = "actions/npm@master"
  args = [ "apt-get update && apt-get install -y git" ]
  runs = "bash -c"
}

action "GitHub Action for npm install" {
  uses = "actions/npm@master"
  args = "install"
  needs = ["GitHub Action for npm apt-get install git"]
}

action "lint:editorconfig" {
  uses = "actions/npm@master"
  args = "lint:editorconfig"
  needs = ["GitHub Action for npm install"]
}

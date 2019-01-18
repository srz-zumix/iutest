workflow "New workflow" {
  on = "push"
  resolves = [
    "lint:editorconfig",
  ]
}

action "lint:editorconfig" {
  uses = "actions/npm@master"
  args = [ "apt-get update && apt-get install -y git && npm install && npm run lint:editorconfig" ]
  runs = "bash -c"
}

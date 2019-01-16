workflow "New workflow" {
  on = "push"
  resolves = [
    "lint:editorconfig",
  ]
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

workflow "Main workflow" {
  on = "push"
  resolves = [
    "lint:editorconfig",
    "Include What You Use",
  ]
}

action "lint:editorconfig" {
  uses = "actions/npm@master"
  args = ["apt-get update && apt-get install -y git && npm install && npm run lint:editorconfig"]
  runs = "bash -c"
}

action "Include What You Use" {
  uses = "./.github/actions/iwyu"
  args = "/work/projects/cmake"
}

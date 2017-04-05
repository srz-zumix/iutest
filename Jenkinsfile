#!/usr/bin/env groovy

def checkout() {
    try {
        checkout scm
    } catch(e) {
        checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [], submoduleCfg: [], userRemoteConfigs: [[url: 'https://github.com/srz-zumix/iutest.git']]])
    }
}

node {
    properties([
        parameters([
            booleanParam(
                defaultValue: false,
                description: 'run config tests',
                name: 'runConfigTests'
            )
        ])
    ])

    step([$class: 'GitHubSetCommitStatusBuilder'])

    stage('checkout') {
        checkout()
    }
    stage('main-test') {
       sh 'cd test && make test'
    }
    stage('config-test') {
        if (params.runConfigTests) {
            stage('disable_feature_param') {
               sh 'cd test/configcheck && make disable_feature_param'
            }
            stage('disable_feature') {
               sh 'cd test/configcheck && make disable_feature_1'
            }
           stage('disable_spec') {
               sh 'cd test/configcheck && make disable_spec'
            }
           stage('combine') {
               sh 'cd test/configcheck && make combine'
            }
           stage('nofeature') {
               sh 'cd test/configcheck && make nofeature'
            }
        } else {
            echo 'skip config tests'
        }
    }
}

#!/usr/bin/env groovy

def checkoutSCM() {
    try {
        checkout scm
    } catch(e) {
        checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [], submoduleCfg: [], userRemoteConfigs: [[url: 'https://github.com/srz-zumix/iutest.git']]])
    }
}

pipeline {
    agent any
    options {
        //disableConcurrentBuilds()
        ansiColor('xterm')
    }
    parameters {
        booleanParam(
            defaultValue: false,
            description: 'run config tests',
            name: 'runConfigTests'
        )
    }

    stages {
        stage('github') {
            steps {
                step([$class: 'GitHubSetCommitStatusBuilder'])
            }
        }
        stage('checkout') {
            steps {
                checkoutSCM()
            }
        }
        stage('main-test') {
            steps {
                sh 'cd test && make test'
            }
        }
        stage('cppcheck') {
            when {
                expression {
                    return fileExists('cppcheck')
                }
            }
            steps {
                sh 'cppcheck --version'
            }
        }
        stage('config-test') {
            when {
                expression {
                    return params.runConfigTests.toBoolean()
                    return boolean.parseBoolean(params.runConfigTests)
                }
            }
            steps {
                sh 'cd test/configcheck && make disable_feature_param'
                sh 'cd test/configcheck && make disable_feature_1'
                sh 'cd test/configcheck && make disable_spec'
                sh 'cd test/configcheck && make combine'
                sh 'cd test/configcheck && make nofeature'
            }
        }
    }
}

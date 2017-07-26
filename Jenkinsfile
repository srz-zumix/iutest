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
                dir('test/configcheck') {
                    sh 'make -j4 disable_feature_param'
                    sh 'make -j4 disable_feature_1'
                    sh 'make -j4 disable_spec'
                    sh 'make -j4 combine'
                    sh 'make -j4 nofeature'
                }
            }
        }
    }
}

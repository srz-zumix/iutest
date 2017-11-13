#!/usr/bin/env groovy
/**
 * Jenkinsfile
 *
 * Copyright (C) 2017, Takazumi Shirayanagi
 * This software is released under the new BSD License,
 * see LICENSE
*/

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
                dir('test') {
                    sh 'make -j4 && make test'
                    sh 'make clean && make -j4 OUTPUTXML=1 && make test OUTPUTXML=1'
                }
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
                    sh 'make disable_feature_param'
                    sh 'make disable_feature_1'
                    sh 'make disable_spec'
                    sh 'make combine'
                    sh 'make nofeature'
                }
            }
        }
    }
    post {
        always {
            junit 'test/*.xml'
        }
    }
}

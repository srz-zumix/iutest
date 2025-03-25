package _Self.buildTypes

import jetbrains.buildServer.configs.kotlin.v2019_2.*
import jetbrains.buildServer.configs.kotlin.v2019_2.buildFeatures.PullRequests
import jetbrains.buildServer.configs.kotlin.v2019_2.buildFeatures.XmlReport
import jetbrains.buildServer.configs.kotlin.v2019_2.buildFeatures.commitStatusPublisher
import jetbrains.buildServer.configs.kotlin.v2019_2.buildFeatures.dockerSupport
import jetbrains.buildServer.configs.kotlin.v2019_2.buildFeatures.pullRequests
import jetbrains.buildServer.configs.kotlin.v2019_2.buildFeatures.xmlReport
import jetbrains.buildServer.configs.kotlin.v2019_2.buildSteps.ScriptBuildStep
import jetbrains.buildServer.configs.kotlin.v2019_2.buildSteps.script
import jetbrains.buildServer.configs.kotlin.v2019_2.triggers.vcs

object GoogleTestCompatibleTest : BuildType({
    name = "GoogleTest Compatible Test"

    artifactRules = "test/**/*.xml"
    publishArtifacts = PublishMode.ALWAYS

    params {
        param("env.MAKE_OPTION", "-j4 USE_GTEST=1")
    }

    vcs {
        root(HttpsGithubComSrzZumixIutestRefsHeadsMaster)
    }
    steps {
        script {
            name = "gtest-compat-1.5.0"
            scriptContent = """
                cd test && mkdir gtest1_5_0
                make clean
                make OUTDIR=gtest1_5_0 OUTPUTXML=1 GTEST_EXPECT_VER=0x01050000 GTEST_EXPECT_LATEST= %env.MAKE_OPTION% test
            """.trimIndent()
            dockerImagePlatform = ScriptBuildStep.ImagePlatform.Linux
            dockerImage = "srzzumix/googletest:release-1.5.0"
        }
        script {
            name = "gtest-compat-1.6.0"
            scriptContent = """
                cd test && mkdir gtest1_6_0
                make clean
                make OUTDIR=gtest1_6_0 OUTPUTXML=1 GTEST_EXPECT_VER=0x01060000 GTEST_EXPECT_LATEST= %env.MAKE_OPTION% test
            """.trimIndent()
            dockerImagePlatform = ScriptBuildStep.ImagePlatform.Linux
            dockerImage = "srzzumix/googletest:release-1.6.0"
        }
        script {
            name = "gtest-compat-1.7.0"
            scriptContent = """
                cd test && mkdir gtest1_7_0
                make clean
                make OUTDIR=gtest1_7_0 OUTPUTXML=1 GTEST_EXPECT_VER=0x01070000 GTEST_EXPECT_LATEST= %env.MAKE_OPTION% test
            """.trimIndent()
            dockerImagePlatform = ScriptBuildStep.ImagePlatform.Linux
            dockerImage = "srzzumix/googletest:release-1.7.0"
        }
        script {
            name = "gtest-compat-1.8.0"
            scriptContent = """
                cd test && mkdir gtest1_8_0
                make clean
                make OUTDIR=gtest1_8_0 OUTPUTXML=1 GTEST_EXPECT_VER=0x01080000 GTEST_EXPECT_LATEST= %env.MAKE_OPTION% test
            """.trimIndent()
            dockerImagePlatform = ScriptBuildStep.ImagePlatform.Linux
            dockerImage = "srzzumix/googletest:release-1.8.0"
        }
        script {
            name = "gtest-compat-1.8.1"
            scriptContent = """
                cd test && mkdir gtest1_8_1
                make clean
                make OUTDIR=gtest1_8_1 OUTPUTXML=1 GTEST_EXPECT_VER=0x01080100 GTEST_EXPECT_LATEST= %env.MAKE_OPTION% test
            """.trimIndent()
            dockerImagePlatform = ScriptBuildStep.ImagePlatform.Linux
            dockerImage = "srzzumix/googletest:release-1.8.1"
        }
        script {
            name = "gtest-compat-1.10.0"
            scriptContent = """
                cd test && mkdir gtest1_10_0
                make clean
                make OUTDIR=gtest1_10_0 OUTPUTXML=1 GTEST_EXPECT_VER=0x01100000 GTEST_EXPECT_LATEST= %env.MAKE_OPTION% test
            """.trimIndent()
            dockerImagePlatform = ScriptBuildStep.ImagePlatform.Linux
            dockerImage = "srzzumix/googletest:release-1.10.0"
        }
        script {
            name = "gtest-compat-1.11.0"
            scriptContent = """
                cd test && mkdir gtest1_11_0
                make clean
                make OUTDIR=gtest1_11_0 OUTPUTXML=1 GTEST_EXPECT_VER=0x01110000 GTEST_EXPECT_LATEST= %env.MAKE_OPTION% test
            """.trimIndent()
            dockerImagePlatform = ScriptBuildStep.ImagePlatform.Linux
            dockerImage = "srzzumix/googletest:release-1.11.0"
        }
    }
    triggers {
        vcs {
            branchFilter = """
                +:master
                +:develop
            """.trimIndent()
        }
    }

    features {
        pullRequests {
            vcsRootExtId = "${HttpsGithubComSrzZumixIutestRefsHeadsMaster.id}"
            provider = github {
                authType = token {
                    token = "******"
                }
                filterAuthorRole = PullRequests.GitHubRoleFilter.EVERYBODY
            }
        }
        commitStatusPublisher {
            vcsRootExtId = "${HttpsGithubComSrzZumixIutestRefsHeadsMaster.id}"
            publisher = github {
                githubUrl = "https://api.github.com"
                authType = personalToken {
                    token = "******"
                }
            }
        }
        dockerSupport {
            loginToRegistry = on {
                dockerRegistryId = "PROJECT_EXT_2"
            }
        }
        xmlReport {
            reportType = XmlReport.XmlReportType.GOOGLE_TEST
            rules = "test/**/*.xml"
        }
    }

    requirements {
        matches("teamcity.agent.jvm.os.family", "Linux")
    }
})

pipeline {
  agent any
  stages {
    stage('parallel') {
      parallel {
        stage('branche 1') {
          stages {
            stage('Compile') {
              steps {
                sh '''make'''
              }
            }
            stage('Compile2') {
              steps {
                sh '''make'''
              }
            }
          }
        }
        stage('branche 2') {
          steps {
            sh '''make
            '''
        }
      }
    }
  }
}

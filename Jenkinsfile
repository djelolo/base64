pipeline {
  agent any
  stages {
    stage('parallel') {
      parallel {
        stage('branche 1') {
          stages {
            stage('Compile') {
              steps {
                sh 'echo Compile'
              }
            }
            stage('Compile2') {
              steps {
                sh 'echo compile2'
              }
            }
          }
        }
        stage('branche 2') {
          steps {
            sh 'echo branche2'
          }
        }
      }
    }
  }
}

pipeline {
  agent any
  stages {
    stage('common') {
      steps {
        sh 'echo common'
      }
    }
    stage('paral') {
      parallel {
        stage('branche1') {
          steps {
            sh 'echo branch1'
          }
        }
        stage('branche2') {
          step {
            sh 'echo branch2'
          }
        }
      }
    }
  }
}
    

pipeline {
  agent any
  stages {
    stage('Make') {
      steps {
        sh 'make'
      }
    }
    stage('Test') {
      parallel {
        stage('Python tests') {
          steps {
            sh 'cd test && nosetests'
          }
        }
        stage('branche2') {
          steps {
            sh 'echo branch2'
          }
        }
      }
    }
  }
}

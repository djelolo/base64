pipeline {
  agent any
  stages {
    stage('Make') {
      steps {
        sh 'make'
      }
    }
    stage('Python tests') {
      steps {
        sh 'cd test && nosetests -v --with-xunit'
      }
    }
  }
  post {
    always {
        junit
            skipPublishingChecks: true,
            testResults: 'test/nosetests.xml'
    }
  }
}

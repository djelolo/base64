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
        archiveArtifacts artifacts: 'test/nosetests.xml', fingerprint: true
        junit skipPublishingChecks: true, testResults: 'test/nosetests.xml'
    }
  }
}

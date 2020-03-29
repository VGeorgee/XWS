let request = require('supertest')
const DEFAULT_PORT = 28015
request = request('http://localhost:' + (DEFAULT_PORT || 80))



;(async function main() {

    for(let i = 0; i < 10; i++){
        await request.get('/simple')
    }

    await request.get('/')
    await request.get('/demofunction')
    await request.get('/favicon.ico')
    try {
        await request.get('/exit')
    } catch (error) {

    }
})()

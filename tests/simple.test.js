let request = require('supertest')
const DEFAULT_PORT = 28015
request = request('http://localhost:' + (DEFAULT_PORT || 80))

reqs = []



;(async function main() {

    for(let i = 0; i < 10; i++){
        reqs.push(await request.get('/simple'))
    }
    
    //Promise.all(reqs)
    
    for(let i = 0; i < 10; i++){
        console.log(reqs[i].text)
    }
    
})()

let request = require('supertest')

request = request('http://localhost')

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

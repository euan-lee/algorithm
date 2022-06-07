function solution(record) {
    const id_val= new Map();
      let answer = [];
    
    for(let i=0;i<record.length;i++){ 
        const [state, uid, name] = record[i].split(' ');        
  
        if(state=="Enter"){
            id_val.set(uid, name);
            answer.push([uid,"님이 들어왔습니다."])
        }
        if(state=="Leave"){
            answer.push([uid,"님이 나갔습니다."])
            //map에서 삭제
        }
        
        if(state=="Change"){
            id_val.set(uid,name);
            //map에서 변경
        }
    }
    return answer.map(ele => id_val.get(ele[0])+ele[1]);
    //console.log(answer)
}

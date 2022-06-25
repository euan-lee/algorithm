function solution(fees, records){
    let id_time = new Map()
    let id_fee= new Map()
    const default_min=fees[0]
    const default_fee=fees[1]
    const unit_min=fees[2]
    const unit_fee=fees[3]
    let time;
    let id;
    let status;
    for(let i=0;i<records.length;i++){
        let split_record=records[i].split(" ")   
        let time_diff=split_record[0].split(":")
            split_record[0]=Number(time_diff[0])*60+Number(time_diff[1])
            time=split_record[0]
            id=Number(split_record[1])
            status=split_record[2]
            if(status=="IN"){
                id_time.set(id,time)
            }
        else{//out
            let timediff=Number(time)-Number(id_time.get(id))
            if(id_fee.has(id)){
                id_fee.set(id,Number(timediff)+Number(id_fee.get(id))) 
            }
            else{
                id_fee.set(id,timediff)   
            }
             id_time.delete(id) 
        }
    }   
   for (const [key, value] of id_time) {
       let last_time=Number(1439)-Number(value)
       if(id_fee.has(key)){
           id_fee.set(key,Number(last_time)+Number(id_fee.get(key))) 
       }
       else{
           id_fee.set(key,last_time)   
       }
    }

     for (const [id,time] of id_fee) {
         if(time>default_min){
            var fee=Number(default_fee)+Math.ceil(Number(time-default_min)/Number(unit_min))*Number(unit_fee)
            id_fee.set(id,fee)   
         }else{
             id_fee.set(id,default_fee)   
         }
     }
    
    let answer1 = [...id_fee];
    answer1.sort((a, b) => a[0] - b[0]); // value값 기준 오름차순정렬
    let answer=[]
   for(let i=0;i<answer1.length;i++){
       //answer.push(answer1[i][1])
       console.log(answer1[i][1])
       answer.push(answer1[i][1])
   }
    return answer;
}

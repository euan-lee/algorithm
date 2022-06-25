function solution(fees, records){
    let map = new Map()
    const default_min=fees[0]
    const default_fee=fees[1]
    const unit_min=fees[2]
    const unit_fee=fees[3]
    let time;
    let id;
    let status;
    for(let i=0;i<records.length;i++){
            let split_record=records[i].split(" ")
            if(split_record[2]=='IN'){
                map.set(split_record[1],split_record[0]);
            }
            else{//out
                 let time=split_record[0].split(":")
                 let time_diff;
                 split_record[0]=Number(time[0])*60+Number(time[1])
                 time_diff=Number(split_record[0])-Number(map.get(split_record[1]))
                 if(time_diff<=default_min){
                     console.log("case1",default_fee)
                     console.log("id",split_record[1])
                     if(map.has('split_record[1]')){
                         let value=Number(default_fee)+Number(map.get('split_record[1]'))
                         map.set('split_record[1]',value)
                         console.log("fee",value)
                     }
                     else{
                         map.set('split_record[1]',default_fee)
                          console.log("fee",default_fee)
                     }
                }
                else{
                    console.log("case2")
                    console.log("id",split_record[1])
                    let fee=Number(default_fee)+(Math.ceil(Number(time_diff)-Number(default_min))/Number(unit_min))*Number(unit_fee)
                     if(map.has('split_record[1]')){
                         let value=Number(fee)+Number(map.get('split_record[1]'))
                         map.set('split_record[1]',value)
                         console.log("fee",value)
                     }
                     else{
                         map.set('split_record[1]',fee) 
                         console.log("fee",fee)
                     }
                }
            }
        
    }
    let answer = [];
    return answer;
}

function solution(progresses, speeds) {
    var answer = [];
    let arr = progresses.map((a,i)=> Math.ceil((100-a)/speeds[i]));
    let cnt = 1;
    let val = 0;
    for(let i =1;i<arr.length;i++){
        if(arr[val] >= arr[i]){
            cnt +=1;
        } else{
            answer.push(cnt);
            val += cnt
            cnt = 1;
        }

        if( i == arr.length-1){
            answer.push(cnt)
        }
    }

    return answer;
}

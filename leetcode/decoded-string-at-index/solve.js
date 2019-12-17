var decodeAtIndex = function(S, K) {
    let size=0n;
    for(let i of S){
        if(isDigit(i)) size *=BigInt(i);
        else size++;
    }
    K = BigInt(K);
        //倒序还原
    for(let i=S.length-1;i>=0;--i){
        K = K%size;
        if(K==0 && !isDigit(S[i])) return S[i];
        if(isDigit(S[i])) size/=BigInt(S[i]);
        else size--;
    }
    return "";
};

var isDigit = function(str){
    return /[0-9]/.test(str);
};

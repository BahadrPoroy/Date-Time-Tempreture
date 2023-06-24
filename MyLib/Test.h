bool SaatTest(int minute){    
    if (minute % 15 == 0){
        return true;
    }
    else{
        return false;
    }
}
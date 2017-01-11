/*
 * Model TACUFF modified 0
 * Without cluster and v=v+2 * alpha
 **/
void T_UFF::apply(int vIndex, bool changing)
{
    
    float   fDeltaV = 0.0f,
    fWeight = 0.0f,
    fVelocity = 0.0f,
    alpha = 0.0f;
    
    int iDeltaV = 0.0f,
    iVel   = 0,
    iDist  = 0,
    iDistEffective = 0,
    iMax   = 0,
    iMyVel = 0,
    iTh  = 0,
    iDeltaVel = 0,
    iHeadway = 0,
    iSafeDist = 0;
    
    
    int iVelVehicle = 0,
    iPosVehicle = 0,
    iDistVehicle = 0;
    
    int iDs = 0;
    
    
    
    Vehicle aheadVehicle;
    Vehicle *pVehicle    = mGrid.getVehiclePointer(vIndex);
    Vehicle **ppVehicle  = &pVehicle;
    tpVehiclesType *type = (*ppVehicle)->type;
    
    if ( (pVehicle->mType & 0x00FFFFFF) == BLOCKED)
        return;
    
    
    iDeltaV = static_cast<int> (type->inc);
    fDeltaV = static_cast<float> (type->inc);
    iMyVel = static_cast<int> ((*ppVehicle)->vx);
    iVel = iMyVel;
    iMax   = min(mParam.vMax, static_cast<int>(type->vMax));
    iHeadway =     max(trunc( static_cast<float> (type->aheadInt) * (*ppVehicle)->alphaNew), 2);
    iSafeDist =    max(trunc( static_cast<float> (type->safeDist) * (*ppVehicle)->alphaNew), 6);
    
    iDist = getDistance2(vIndex, &aheadVehicle);
    
    iPosVehicle    = mGrid.getGrid(aheadVehicle.x, aheadVehicle.y);
    
    iDistVehicle   = getDistance(iPosVehicle, NULL);
    
    int iDeltaD = iDistVehicle - iDist;
    
    
    
    alpha = betaFunction(type->param);
    
    if (aheadVehicle.ID != 0xFFFFFFFF)
        iDeltaVel = (iMyVel+iDeltaV) - static_cast<int> (aheadVehicle.vx);
    
    float   facc = fDeltaV * alphaFunction( alpha );
    
    
    //    fWeight = 2.5f;
    fWeight = 0.0f;
    
    if (iDeltaVel > 0){
        iTh = iDist / iDeltaVel;
        
        float fDeltaD = static_cast<float> (iDeltaD);
        
        
        if (fDeltaD <= (fDeltaV * alphaFunction((*ppVehicle)->alphaOld))){
            fWeight += (fDeltaV * alphaFunction((*ppVehicle)->alphaOld));
            
        }
        
        
        if (iTh < iHeadway){ //Headway -1 (importante pq define no perfil          ORIGINAL(3)
            fWeight += static_cast<float> (iSafeDist);
            
        }
        
        //        fWeigh= 3.0f;
        
        //        fWeight = max(fWeight, 0.0f);
    }
    
    facc = max(facc - fWeight, 0.0f);
    //truncFloor
    int     iacc =  truncCurve3(facc);
    //int     iacc =  truncFloor(facc);
    
    iVel += max(iacc, 0);
    
    iVel  = min( iVel, iMax );
    
    assert (iVel >= 0);
    
    //Monte Carlo
    (*ppVehicle)->alphaNew = betaFunction(type->param + 5); //deslocamento para acessar o vetor....
    
    //fAlfaDist  = (*ppVehicle)->alphaNew;
    
    assert((*ppVehicle)->alphaNew >= 0.0f);
    assert((*ppVehicle)->alphaNew <= 1.0f);
    
    
    if (iDist < iMax)
    {
        
        if (aheadVehicle.ID != 0xFFFFFFFF){
            
            
            tpVehiclesType *type = aheadVehicle.type;
            //            iDeltaV =  static_cast<int> (type->inc);
            //            fDeltaV = static_cast<float> (type->inc);
            fDeltaV = fDeltaV * alphaFunction((*ppVehicle)->alphaOld);
            
            //  cerr << (*ppVehicle)->ID << " " << alphaFunction((*ppVehicle)->alphaOld) << " " 
	    //<< alphaFunction(aheadVehicle.alphaOld) << endl;
            //"i+1

            //cerr << (*ppVehicle)->ID << " = " << fDeltaV << " " << fWeight << " " 
            //<< iDistVehicle << " " <<  iDist << " " << iDeltaD << " Velocidade: " 
            //<< (int) (*ppVehicle)->vx << " " << (int) aheadVehicle.vx << " ith = " 
            //<< iTh << " iHeadway "<< iHeadway << endl;
            float fds = max(fDeltaV - fWeight, 0.0f);
            fVelocity     = static_cast<float> (aheadVehicle.vx) + fds;
            
            iVelVehicle    = trunc(fVelocity);
            
            // fWeight  = fDeltaV;
            iVelVehicle = min(iVelVehicle, iMax);
            
            iDistEffective = min(iDistVehicle, iVelVehicle);
            
            
            
            
        }else
            iDistEffective = 0; //type->vMax;
    }else {
        fVelocity = 0.0f;
        iDistEffective  = 0; //type->vMax;
    }
    
    
    // iDs = static_cast <int> (ceil(fWeight));
    assert(iDistEffective >= 0);
    //iDistEffective = max(iDistEffective, 0);
    iDist += iDistEffective;
    
    
    
    assert(iVel <= 25);
    iVel  = min(iVel, iDist );
    
    (*ppVehicle)->vxNew = static_cast <unsigned char> (iVel);
    
    
};


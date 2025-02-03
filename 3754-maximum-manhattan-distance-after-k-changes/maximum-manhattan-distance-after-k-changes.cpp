class Solution {
public:
    int maxDistance(string u, int k) {
        int n = 0, w = 0, s = 0, e = 0, l = 0,v=0,h=0;
        for (char c : u) {
            if (c == 'N') {
                n++;
                v++;
                if(v>=0 && h>=0){
                    if(k>=s+w){
                        l = max(l,v+h+2*(s+w));
                    }else{
                        l = max(l,v+h+2*k);
                    }
                    continue;
                }
                if(v>=0 && h<0){
                    if(k>=s+e){
                        l = max(l,v+abs(h)+2*(s+e));
                    }else{
                        l = max(l,v+abs(h)+2*k);
                    }
                    continue;
                }
                if(v<0 && h>=0){
                    if(k>=n+w){
                        l = max(l,abs(v)+h+2*(n+w));
                    }else{
                        l = max(l,abs(v)+h+2*k);
                    }
                    continue;
                }
                if(v<0 && h<0){
                    if(k>=n+e){
                        l = max(l,abs(v)+abs(h)+2*(n+e));
                    }else{
                        l = max(l,abs(v)+abs(h)+2*k);
                    }
                    continue;
                }
            }
            if (c == 'W') {
                w++;
                h--;
                if(v>=0 && h>=0){
                    if(k>=s+w){
                        l = max(l,v+h+2*(s+w));
                    }else{
                        l = max(l,v+h+2*k);
                    }
                    continue;
                }
                if(v>=0 && h<0){
                    if(k>=s+e){
                        l = max(l,v+abs(h)+2*(s+e));
                    }else{
                        l = max(l,v+abs(h)+2*k);
                    }
                    continue;
                }
                if(v<0 && h>=0){
                    if(k>=n+w){
                        l = max(l,abs(v)+h+2*(n+w));
                    }else{
                        l = max(l,abs(v)+h+2*k);
                    }
                    continue;
                }
                if(v<0 && h<0){
                    if(k>=n+e){
                        l = max(l,abs(v)+abs(h)+2*(n+e));
                    }else{
                        l = max(l,abs(v)+abs(h)+2*k);
                    }
                    continue;
                }
            }
            if (c == 'S') {
                s++;
                v--;
                if(v>=0 && h>=0){
                    if(k>=s+w){
                        l = max(l,v+h+2*(s+w));
                    }else{
                        l = max(l,v+h+2*k);
                    }
                    continue;
                }
                if(v>=0 && h<0){
                    if(k>=s+e){
                        l = max(l,v+abs(h)+2*(s+e));
                    }else{
                        l = max(l,v+abs(h)+2*k);
                    }
                    continue;
                }
                if(v<0 && h>=0){
                    if(k>=n+w){
                        l = max(l,abs(v)+h+2*(n+w));
                    }else{
                        l = max(l,abs(v)+h+2*k);
                    }
                    continue;
                }
                if(v<0 && h<0){
                    if(k>=n+e){
                        l = max(l,abs(v)+abs(h)+2*(n+e));
                    }else{
                        l = max(l,abs(v)+abs(h)+2*k);
                    }
                    continue;
                }
            }
            if (c == 'E') {
                e++;
                h++;
                if(v>=0 && h>=0){
                    if(k>=s+w){
                        l = max(l,v+h+2*(s+w));
                    }else{
                        l = max(l,v+h+2*k);
                    }
                    continue;
                }
                if(v>=0 && h<0){
                    if(k>=s+e){
                        l = max(l,v+abs(h)+2*(s+e));
                    }else{
                        l = max(l,v+abs(h)+2*k);
                    }
                    continue;
                }
                if(v<0 && h>=0){
                    if(k>=n+w){
                        l = max(l,abs(v)+h+2*(n+w));
                    }else{
                        l = max(l,abs(v)+h+2*k);
                    }
                    continue;
                }
                if(v<0 && h<0){
                    if(k>=n+e){
                        l = max(l,abs(v)+abs(h)+2*(n+e));
                    }else{
                        l = max(l,abs(v)+abs(h)+2*k);
                    }
                    continue;
                }
            }
        }
        return l;
    }
};
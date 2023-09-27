from typing import Any

class Edge(object):
    def __init__(self, v_from: int, v_to:int,weight:Any):
        self.v_from = v_from
        self.v_to = v_to
        self.weight = weight
    
    def get_from(self)->int:
        return self.v_from
    
    def get_to(self)->int:
        return self.v_to
    
    def get_weight(self)->Any:
        return self.weight
    
    def get_other_v(self,v:int)->int:
        if v==self.v_from:
            return self.v_to
        else:
            return self.v_from


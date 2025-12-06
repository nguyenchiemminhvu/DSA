from typing import List

class Solution:
    def minNumberOfHours(self, cur_energy: int, cur_exp: int, energy: List[int], exp: List[int]) -> int:
        need_energy = 0
        need_exp = 0

        n = len(energy)
        for i in range(n):
            op_energy, op_exp = energy[i], exp[i]
            if cur_energy <= op_energy:
                need_energy += op_energy - cur_energy + 1
                cur_energy = op_energy + 1
            if cur_exp <= op_exp:
                need_exp += op_exp - cur_exp + 1
                cur_exp = op_exp + 1
                
            cur_exp += op_exp
            cur_energy -= op_energy

        return need_energy + need_exp
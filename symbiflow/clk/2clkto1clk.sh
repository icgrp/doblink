#!/bin/bash
sed -i '/input wire clk_user,/d' $*/leaf.v
sed -i 's/(clk_user)/(clk_bft)/' $*/leaf.v

use_bpm 120

p1 = [chord(:E3,"minor7"),
      chord(:C3,"minor7"),
      chord(:D3,"major"),
      chord(:E3,"m11")
      ]
with_synth :piano do
  p1.each{
    |c|
    play c ,amp: 2 , decay: 1
    sleep 3
  }
end
with_synth :piano do
  live_loop :piano do
    p1.each{
      |c|
      play c ,amp: 2 ,decay: 3.5
      sleep 4
    }
  end
end
sleep 16
def tond(v)
  sample :drum_cymbal_closed, amp: 1.25*v
end
live_loop :br do
  v = [0,0,1,0,0,1,1,0,1,1,0,1,1,0,1,0]
  v.each{
    |v|
    tond(v)
    sleep 0.5
  }
end
sleep 16
live_loop :kick do
  sample :bd_mehackit,amp: 2
  sleep 5
  sample :bd_mehackit,amp: 2
  sleep 3
end
sleep 16
def sn(v)
  sample :bd_fat ,amp: 2*v
  sample :sn_dolf ,amp: v
end

live_loop :sn do
  volume = [0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1]
  volume.each{
    |v|
    sn(v)
    sleep 1
  }
end

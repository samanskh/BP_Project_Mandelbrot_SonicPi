use_bpm 120
p1 = [chord(:E3,"minor7"),
      chord(:C3,"minor7"),
      chord(:D3,"major"),
      chord(:E3,"m11"),
      ]
with_synth :piano do
  live_loop :piano do
    p1.each{
      |c|
      play c, amp: 1.5 , decay: 3.5
      sleep 4
    }
  end
end

live_loop :kick do
  sample :bd_mehackit,amp: 2
  sleep 5
  sample :bd_mehackit,amp: 2
  sleep 3
end
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

live_loop :pedal do
  sample :drum_cymbal_pedal
  sleep 1
end

def tond1(v)
  sample :drum_cymbal_pedal, amp: v
end

live_loop :dr do
  v = [0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0]
  v.each{
    |v|
    tond1(v)
    sleep 0.25
  }
  sleep 32
end











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
sleep 16
sample_path = "C:/git/FC02031.copy/samples/mystic-hypnotic-saxophone-melody_117bpm_F_major.wav"

sample sample_path, pitch: 2, rate: 1, amp: 2


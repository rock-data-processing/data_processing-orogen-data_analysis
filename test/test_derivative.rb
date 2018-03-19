require 'orocos'
Orocos.initialize
Orocos.conf.load_dir("config")

Orocos.run 'data_analysis::DerivativeSGTask' => 'derivative' do

  derivative = Orocos.name_service.get 'derivative'
  Orocos.conf.apply(derivative, ['default'])

  derivative.configure
  derivative.start

  input = Types.base.samples.Joints.new
  input.elements = [Types.base.JointState.new]*20

  reader = derivative.joints_out.reader

  dt = 0.01
  t = 0
  puts "Press Ctrl-C to exit"

  while true
     input.elements.each do |e|
         e.position = Math.sin(t + 0.1*Random.rand - 0.05)
     end
     input.time = Types.base.Time.now

     derivative.joints.write(input)

      t = t + dt
     sleep(dt)
  end
end

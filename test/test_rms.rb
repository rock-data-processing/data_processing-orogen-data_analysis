require "orocos"
Orocos.initialize
Orocos.conf.load_dir("config")

Orocos.run "data_analysis::RMSTask" => "rms" do
    task = Orocos::TaskContext.get "rms"
    Orocos.conf.apply(task, ["default", "rbs"])
    task.configure
    task.start

    writer = task.rbs.writer
    input_data = Types.base.samples.RigidBodyState.new
    reader = task.rms.reader

    while true
        input_data.position = Types.base.Vector3d.new(Random.rand,2*Random.rand,3*Random.rand)
        writer.write input_data
        sleep 0.1
        sample = reader.read
        if sample
            puts "Input data:    " + input_data.position.to_a.to_s
            puts "RMS:           " + sample.to_s
            puts "................................."
        end
    end
end

require "orocos"
Orocos.initialize
Orocos.conf.load_dir(".")

Orocos.run "data_analysis::Norm" => "norm" do
    task = Orocos::TaskContext.get "norm"
    Orocos.conf.apply(task, ["default"])
    task.configure
    task.start

    writer = task.rbs.writer

    input_data = Types.base.samples.RigidBodyState.new
    input_data.position = Types.base.Vector3d.new(-1,2,-3)

    reader = task.norm_rbs.reader

    while true
        writer.write input_data
        sleep 0.1
        sample = reader.read
        if sample
            puts "Input data:    " + input_data.position.to_a.to_s
            puts "Norm:          " + sample.to_s
            puts "................................."
        end
    end
end

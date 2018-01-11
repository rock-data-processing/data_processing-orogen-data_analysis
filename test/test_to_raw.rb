require "orocos"
Orocos.initialize
Orocos.conf.load_dir(".")

Orocos.run "data_analysis::ToRaw" => "to_raw" do
    task = Orocos::TaskContext.get "to_raw"
    Orocos.conf.apply(task, ["default"])
    task.configure
    task.start

    writer = task.rbs.writer
    reader = task.raw_rbs.reader

    input_data = Types.base.samples.RigidBodyState.new
    input_data.position = Types.base.Vector3d.new(rand(),rand(),rand())

    while true
        input_data.time = Types.base.Time.now()
        writer.write input_data
        sleep 0.1
        sample = reader.read
        if sample
            puts "Input data: " + input_data.position.data.to_s
            puts "Raw:        " + sample.to_a.to_s
            puts "................................."
        end
    end
end

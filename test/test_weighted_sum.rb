require "orocos"
Orocos.initialize
Orocos.conf.load_dir("config")

Orocos.run "data_analysis::WeightedSumTask" => "weighted_sum" do
    task = Orocos::TaskContext.get "weighted_sum"
    Orocos.conf.apply(task, ["default", "rbs"])
    task.configure
    task.start

    writer_1 = task.rbs_1.writer
    writer_2 = task.rbs_2.writer

    input_1 = Types.base.samples.RigidBodyState.new
    input_2 = Types.base.samples.RigidBodyState.new
    input_1.position = Types.base.Vector3d.new(1,2,3)
    input_2.position = Types.base.Vector3d.new(4,5,6)

    reader = task.weighted_sum.reader

    puts "Press Ctrl-C to exit"

    while true
        input_1.time = Types.base.Time.now
        input_2.time = Types.base.Time.now
        writer_1.write input_1
        writer_2.write input_2
        sleep 1
        sample = reader.read
        if sample
            puts "Input data 1:    " + input_1.position.to_a.to_s
            puts "Input data 2:    " + input_2.position.to_a.to_s
            puts "Weights:         " + task.weights.to_s
            puts "Weighted sum:    " + sample.to_s
            puts
        end
    end
end

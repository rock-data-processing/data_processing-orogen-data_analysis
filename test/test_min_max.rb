require "orocos"
Orocos.initialize
Orocos.conf.load_dir("config")

Orocos.run "data_analysis::MinMaxTask" => "min_max" do
    task = Orocos::TaskContext.get "min_max"
    Orocos.conf.apply(task, ["default", "rbs"])
    task.configure
    task.start

    writer = task.rbs.writer
    input_data = Types.base.samples.RigidBodyState.new
    reader_min = task.min.reader
    reader_max = task.max.reader
    reader_min_coef = task.min_coef.reader
    reader_max_coef = task.max_coef.reader

    while true
        input_data.position = Types.base.Vector3d.new(Random.rand,2*Random.rand,3*Random.rand)
        writer.write input_data
        sleep 0.1
        min = reader_min.read
        max = reader_max.read
        min_coef = reader_min_coef.read
        max_coef = reader_max_coef.read
        if max_coef
            puts "Input data:    " + input_data.position.to_a.to_s
            puts "Min:           " + min.to_s
            puts "Max:           " + max.to_s
            puts "Min Coef.:     " + min_coef.to_s
            puts "Max Coef.:     " + max_coef.to_s
            puts "................................."
        end
    end
end

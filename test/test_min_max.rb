require "orocos"
Orocos.initialize
Orocos.conf.load_dir("config")

Orocos.run "data_analysis::MinMaxTask" => "min_max" do
    task = Orocos::TaskContext.get "min_max"
    Orocos.conf.apply(task, ["default"])
    task.configure
    task.start

    writer_rbs = task.rbs.writer
    input_rbs  = Types.base.samples.RigidBodyState.new
    reader_rbs_min = task.min_rbs.reader
    reader_rbs_max = task.max_rbs.reader

    writer_joints = task.joints.writer
    input_joints = Types.base.samples.Joints.new
    input_joints.elements = [Types.base.JointState.new]*2
    reader_joints_min = task.min_joints.reader
    reader_joints_max = task.max_joints.reader

    while true
        input_rbs.position = Types.base.Vector3d.new(1 + 0.1*Random.rand - 0.05, 2 + 0.1*Random.rand - 0.05, 3 + 0.1*Random.rand - 0.05)
        input_joints.elements[0].position = 4.0 + 0.1*Random.rand - 0.05
        input_joints.elements[1].position = 5.0 + 0.1*Random.rand - 0.05

        input_rbs.time = Types.base.Time.now
        writer_rbs.write input_rbs
        input_joints.time = Types.base.Time.now
        writer_joints.write input_joints

        sleep 0.1
        sample_rbs_min = reader_rbs_min.read
        sample_rbs_max = reader_rbs_max.read
        if sample_rbs_min && sample_rbs_max
            puts "RBS port:"
            puts "Input data:    " + input_rbs.position.to_a.to_s
            puts "Min:           " + sample_rbs_min.to_s
            puts "Max:           " + sample_rbs_max.to_s
            puts
        end
        sample_joints_min = reader_joints_min.read
        sample_joints_max = reader_joints_max.read
        if sample_joints_min && sample_joints_max
            puts "Joints port:"
            puts "Input data:    [" + input_joints.elements[0].position.to_s + " " + input_joints.elements[1].position.to_s + "]"
            puts "Min:           " + sample_joints_min.to_s
            puts "Max:           " + sample_joints_max.to_s
            puts "................................."
        end
    end
end

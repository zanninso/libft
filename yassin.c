color ray_color(const ray &r, const color &background, const hittable &world, int depth)
{
    hit_record rec;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);
    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return background;
    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;
    return emitted + attenuation * ray_color(scattered, background, world, depth - 1);
}

color ray_color(const ray &r, const color &background, const hittable &world, int depth)
{
    hit_record rec;
    color *ray_colors;
    color ret;
    while ()
    {
        if (depth <= 0)
        {
            ret = color(0,0,0);
            break;
        }
        if (!world.hit(r, 0.001, infinity, rec))
        {
            ret = color(0,0,0);
            break;
        }
        ray scattered;
        color attenuation;
        color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            ret = emitted;
            break;
        }
        r = scattered;
        depth--;
        //store i list attenuation emitted
    }
    while(stored list)
    {
        ret =  list.emitted + list.attenuation * ret;
        list = list.next;
    }
    return (ret)
}